class Screen {
    int width;
    int height;
    int bpp;
    bool update;
    string title;
    string footer;
    SDL_Surface *surface;
  public:
    Screen(int, int, int, string);
    ~Screen();
};
