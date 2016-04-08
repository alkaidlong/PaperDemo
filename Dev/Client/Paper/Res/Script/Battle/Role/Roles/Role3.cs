#include "Role.cs"

class Role3 : Role
{
    Role3()
    {
         IconName = "PantheonIcon.png";
         StarCount = 1;

         WalkName = "PantheonWalk.ani";
         RunName = "PantheonRun.ani";
//          Attack1Name = "PantheonAttack.ani";
//          Attack2Name = "PantheonAttack.ani";
//          Attack3Name = "PantheonAttack.ani";
//          Attack4Name = "PantheonAttack.ani";
//          Attack5Name = "PantheonAttack.ani";
         IdleName = "PantheonIdle.ani";
         RestName = "PantheonIdle.ani";
         WinName = "PantheonVictory.ani";
         HitName = "PantheonHitInterrupt.ani";
         HitDownName = "PantheonKnockedDown.ani";
         HitBackName = "PantheonWereRepulsed.ani";
         WaitName = "";
         DeadName = "PantheonDeath.ani";

         PropertyID = 3;
	     PropertyLevel = 3;

//         StandDistanceToTarget = 200.0f;
         RoleWidth = 158.0f;
         RoleHeight = 120.0f;
         RoleXOffset = -79.0f;
         RoleYOffset = 0.0f;
    }

    ~Role3()
    {

    }

}