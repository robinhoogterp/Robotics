class Camera_Input
{
private:
    static Camera_Input *instance;
    int xPos;
    Camera_Input();
    ~Camera_Input();
    int file_desc;
    char *buffer;
    char *myfifo_read;

public:
    void Init();
    static Camera_Input *GetInstance();
    void ReadFile();
    int GetPos();
    void SetPOs(int pos);
};



