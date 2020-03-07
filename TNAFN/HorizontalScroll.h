#include "Camera.h"
class HorizontalScroll
{
public:
	HorizontalScroll();

	//Makes sure that the camera is following the focus
	void Update();

	//Getters
	Camera* GetCam() const;
	Transform* GetFocus() const;
	float GetOffset() const;
	float GetDifference();
	float GetMaxOffSet();
	float GetMinOffSet();
	//Setters
	void SetCam(Camera* cam);
	void SetFocus(Transform* focus);
	void SetOffset(float offset);


private:
	Camera* m_cam = nullptr;
	Transform* m_focus = nullptr;

	float m_offset = 5.f;

	float difference= 0;
	float MaxOffSet = 0;
	float MinOffSet = 0;
};

//Sends vertical scrolling camera TO json file
inline void from_json(const nlohmann::json& j, HorizontalScroll& horiScroll) {
	horiScroll.SetOffset(j["XOffset"]);
}

inline void to_json(nlohmann::json& j, const HorizontalScroll& horiScroll) {
	j["XOffset"] = horiScroll.GetOffset();
}