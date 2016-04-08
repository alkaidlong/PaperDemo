#include "Role.cs"

class Role2 : Role
{
    Role2()
    {
         IconName = "LuxIcon.png";
         StarCount = 1;

         WalkName = "LuxWalk.ani";
         RunName = "LuxRun.ani";
//          Attack1Name = "LuxAttack.ani";
//          Attack2Name = "LuxAttack.ani";
//          Attack3Name = "LuxAttack.ani";
//          Attack4Name = "LuxAttack.ani";
//          Attack5Name = "LuxAttack.ani";
         IdleName = "LuxIdle.ani";
         RestName = "LuxIdle.ani";
         WinName = "LuxVictory.ani";
         HitName = "LuxHitInterrupt.ani";
         HitDownName = "LuxKnockedDown.ani";
         HitBackName = "LuxWereRepulsed.ani";
         WaitName = "";
         DeadName = "LuxDeath.ani";

         PropertyID = 2;
	     PropertyLevel = 2;

 //        StandDistanceToTarget = 600.0f;
         RoleWidth = 72.0f;
         RoleHeight = 120.0f;
         RoleXOffset = -36.0f;
         RoleYOffset = 0.0f;
    }

    ~Role2()
    {

    }


}