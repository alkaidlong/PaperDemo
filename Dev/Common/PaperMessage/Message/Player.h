#pragma once

#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/StringRef.h"
#include "RealtimeRoleProperty.h"

USING_MEDUSA;

class Player
{
public:
	Player(void);
	~Player(void);

	void ResetToDefault();
	void Update(float dt);
};

