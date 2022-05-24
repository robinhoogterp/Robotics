class Controller_Input{
    private:
    static Controller_Input *instance;
    int xPos1, xPos2, yPos1, yPos2;
    bool btn1, btn2, btn3, btn4, btn5, btn6;
    Controller_Input();
    ~Controller_Input();
    char *buffer;

    public:
        void Init();
        static Controller_Input *GetInstance();
        void ReadFile();
        int * GetPositions();
        bool * GetButtons();
        void SetPOs(int pos);
}
