#pragma once
#include "Platform/Platform.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/Geometry/GeometryDefines.h"

USING_MEDUSA;

enum class ToastPosition
{
	Top=0,
	Center=1,
	Bottom=2
};

class SystemUI:public Pattern::Singleton<SystemUI>
{
	friend class Pattern::Singleton<SystemUI>;
	SystemUI(void);
	~SystemUI(void){}
public:

#ifdef MEDUSA_ANDROID
	typedef void ShowAlertViewCallback(const char * pszMsg, const char * pszTitle);
	void SetShowAlertViewCallback(ShowAlertViewCallback* callback){mShowAlertViewCallback=callback;}
#endif


	void ShowActivityIndicator();
	void HideActivityIndicator();

	void ShowAlertView(StringRef text,Pattern::Action0 callback=Pattern::Action0::Empty);
	void ShowAlertView(WStringRef text,Pattern::Action0 callback=Pattern::Action0::Empty);

	void ShowToast(StringRef text, float duration = 2.0f, ToastPosition position = ToastPosition::Center);

	Medusa::OrientationMask GetSupportedOrientation() const { return mSupportedOrientation; }
	void SetSupportedOrientation(Medusa::OrientationMask val) { mSupportedOrientation = val; }

	bool IsAutoRotateEnabled() const { return mAutoRotateEnabled; }
	void EnableAutoRotate(bool val) { mAutoRotateEnabled = val; }
private:
    void* mActivityIndicatorView;

#ifdef MEDUSA_ANDROID
	ShowAlertViewCallback* mShowAlertViewCallback;
#endif


	OrientationMask mSupportedOrientation;
	bool mAutoRotateEnabled;
	

};

