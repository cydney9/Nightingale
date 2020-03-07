#include "HorizontalScroll.h"

HorizontalScroll::HorizontalScroll()
{
}

void HorizontalScroll::Update()
{
	MaxOffSet = m_cam->m_localPosition.x + m_offset;
	MinOffSet = m_cam->m_localPosition.x - m_offset;
	//Above focus
	if (m_focus->GetPosition().x > m_cam->m_localPosition.x + m_offset) {
		//Calculate the amount the focus has "pushed" the camera right by
		difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x + m_offset);
		//Adjust the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x + difference, m_cam->GetPosition().y, m_cam->GetPosition().z));
	}

	//Below focus
	if (m_focus->GetPosition().x < m_cam->m_localPosition.x - m_offset) {
		//Calculate the amount the focus has "pushed" the camera left by
		difference = m_focus->GetPosition().x - (m_cam->m_localPosition.x - m_offset);
		//Abjust the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x + difference, m_cam->GetPosition().y, m_cam->GetPosition().z));
	}
}

Camera* HorizontalScroll::GetCam() const
{
	return m_cam;
}

Transform* HorizontalScroll::GetFocus() const
{
	return m_focus;
}

float HorizontalScroll::GetOffset() const
{
	return m_offset;
}

float HorizontalScroll::GetDifference()
{
	return difference;
}

float HorizontalScroll::GetMaxOffSet()
{
	return MaxOffSet;
}
float HorizontalScroll::GetMinOffSet()
{
	return MinOffSet;
}
void HorizontalScroll::SetCam(Camera* cam)
{
	m_cam = cam;
}

void HorizontalScroll::SetFocus(Transform* focus)
{
	m_focus = focus;
}

void HorizontalScroll::SetOffset(float offset)
{
	m_offset = offset;
}
