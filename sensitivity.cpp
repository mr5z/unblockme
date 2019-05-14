/*
 *  Make sure project type is windows application
 */
 
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include<cmath>
 
float sensitivity = 0.7f;
 
 
LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
 
   // Let windows handle mouse clicks
   if (wParam != WM_MOUSEMOVE) {
      return CallNextHookEx(NULL, nCode, wParam, lParam);
   }
 
   // Get event information
   PMSLLHOOKSTRUCT p = reinterpret_cast<PMSLLHOOKSTRUCT>( lParam );
 
   // Old mouse location
   static float ox = static_cast<float>( p->pt.x );
   static float oy = static_cast<float>( p->pt.y );
 
   // Mouse location without sensitivity changed
   float x = static_cast<float>( p->pt.x );
   float y = static_cast<float>( p->pt.y );
    
   // New mouse location
   float nx = ox + (x - ox) * sensitivity;
   float ny = oy + (y - oy) * sensitivity;
 
   // Set cursor position
   SetCursorPos(
      static_cast<int>( nx ),
      static_cast<int>( ny )
   );
 
   // Set old location ready for next time
   ox = nx;
   oy = ny;
 
   return 1;
}
 
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nShowCmd) {
 
   // Set mouse hook
   HHOOK mouseHook = SetWindowsHookEx(
                  WH_MOUSE_LL,      /* Type of hook */
                  mouseHookProc,    /* Hook process */
                  hInstance,        /* Instance */
                  NULL);
 
   // Wait for user to exit
   MessageBox(NULL, "Press OK to close.", "", MB_OK);
   return 0;
}