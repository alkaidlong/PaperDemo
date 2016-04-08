enum RoleAction
{
	Walk,
	Run,
	Attack,
	Idle,
	Rest,
	Win,
	Hit,
	HitDown,
	HitBack,
	Wait,
	Dead
};

enum State 
{
    Battle,
    Show
}

enum BattleState 
{
    Normal,
    Pause,
    Over
}

enum SkillType 
{
    AttackEnemy,
    HelpSelf
}