#include <SDL.h>

int main(int argc, char *argv[]) {
  SDL_Window* window;
  SDL_Render* render;
  SDL_Event e;

  bool q = 0;
  int sdl = SDL_Init(SDL_INIT_EVERYTHING);

  if(0 <= sdl ){
        // 当 SDL 初始化完成后创建一个标题为 "SDL Window" 的窗口, 窗口对齐方式为居中对齐，分辨率为 640x480 的窗口
        g_pWindow=SDL_CreateWindow("SDL Window",
            SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
            640,480,SDL_WINDOW_SHOWN);
        if(0 != window)
            render=SDL_CreateRenderer(window,-1,0);  
    }
    SDL_SetRenderDrawColor(render,0,255,255,255);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);

    while( 0 == q )
    {
       while( 0 != SDL_PollEvent( &e ) )
                {
                    // 检测到用户需要退出
                    if( e.type == SDL_QUIT )
                        q = true;
                }
    }
    SDL_Quit();
    return 0;
}
