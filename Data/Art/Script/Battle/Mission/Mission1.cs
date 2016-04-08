#include "Mission.cs"

class Mission1 : Mission
{  
    Mission1()
    {
        BGMoveTime = 60.0f;
    }

    ~Mission1()
    {
    
    }

    void LoadResource() 
    {
        
    }

    void Initialize() 
    {
        mBGAdds.insertLast(Game::AddMissionBGLayer("Mission1Scene1.layer",1));
        mBGAdds.insertLast(Game::AddMissionBGLayer("Mission1Scene2.layer",-1));
        mBGAdds.insertLast(Game::AddMissionBGLayer("Mission1Scene3.layer",-2));
        mBGAdds.insertLast(Game::AddMissionBGLayer("Mission1Scene4.layer",-3));
        mBGAdds.insertLast(Game::AddMissionBGLayer("Mission1Scene5.layer",-4));
        Mission::Initialize();
        

        //mIsMoveCamer = true;
    }

    void Uninitialize() 
    {
    
    }

    void Update(float dt) 
    {
        Mission::Update(dt);
    }

    void BGMoveDone()
    {
    
    }

}