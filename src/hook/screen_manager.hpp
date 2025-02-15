class ScreenManager
{
  public:
   [[nodiscard]] static ScreenManager* GetSingleton()
   {
      static ScreenManager singleton;
      return &singleton;
   }

   // TODO: figure out exact struct
   struct ScreenTile
   {
      uint8_t screen;
      uint8_t screen_limit;
      long tex_pos;
      long texpos_lower;
      long texpos_anchored;
      long texpos_anchored_x;
      long texpos_anchored_y;
      uint32_t texpos_flag;
   };

   enum ScreenType
   {
      Main,
      Top
   };

   template <ScreenType screen_type>
   ScreenTile* GetTile(int x, int y)
   {
      if (screen_type == ScreenType::Top) {
         return reinterpret_cast<ScreenTile*>(this->screen_top + x * this->dimy * 4 + y * 4);
      } else {
         return reinterpret_cast<ScreenTile*>(this->screen + x * this->dimy * 4 + y * 4);
      }
   }

   template <ScreenType screen_type>
   ScreenTile* GetOffset(int offset)
   {
      if (screen_type == ScreenType::Top) {
         return reinterpret_cast<ScreenTile*>(this->screen_top + offset * 4);
      } else {
         return reinterpret_cast<ScreenTile*>(this->screen + offset * 4);
      }
   }

   void AllocateScreen(int x, int y)
   {
      this->dimx = x;
      this->dimy = y;
      this->screen = new unsigned long[x * y * 14];
      this->screen_top = new unsigned long[x * y * 14];
   }

   template <ScreenType screen_type>
   void ClearScreen()
   {
      if (screen_type == ScreenType::Top) {
         if (this->screen_top != nullptr) {
            delete[] this->screen_top;
         }
         this->screen_top = nullptr;
      } else {
         if (this->screen != nullptr) {
            delete[] this->screen;
         }
         this->screen = nullptr;
      }
   }

   template <ScreenType screen_type>
   void ClearTile(int x, int y, int len = 1)
   {
      for (int i = 0; i < len; i++) {
         auto tile = GetTile<screen_type>(x + i, y);
         tile->tex_pos = 0;
      }
   }

   template <ScreenType screen_type>
   void ResetScreen()
   {
      this->ClearScreen<screen_type>();
      if (screen_type == ScreenType::Top) {
         this->screen_top = new unsigned long[this->dimx * this->dimy * 14];
      } else {
         this->screen = new unsigned long[this->dimx * this->dimy * 14];
      }
   }

   bool isInitialized() { return this->screen != nullptr && this->screen_top != nullptr; }

  private:
   ScreenManager() {}
   ScreenManager(const ScreenManager&) = delete;
   ScreenManager(ScreenManager&&) = delete;

   ~ScreenManager()
   {
      delete[] this->screen;
      delete[] this->screen_top;
      delete this;
   };

   int32_t dimx;
   int32_t dimy;
   unsigned long* screen;
   unsigned long* screen_top;
};