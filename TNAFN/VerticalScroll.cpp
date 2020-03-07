#include "VerticalScroll.h"

VerticalScroll::VerticalScroll()
{
}

void VerticalScroll::Update()
{
	//Above focus
	if (m_focus->GetPosition().y > m_cam->m_localPosition.y + m_offset) {
		//Calculate the amount the focus has "pushed" the camera right by
		//Adjust the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x , m_cam->GetPosition().y + m_focus->GetPosition().y - (m_cam->m_localPosition.y + m_offset), m_cam->GetPosition().z));
	}

	//Below focus
	if (m_focus->GetPosition().y < m_cam->m_localPosition.y - m_offset) {
		//Calculate the amount the focus has "pushed" the camera left by
		//Abjust the camera
		m_cam->SetPosition(vec3(m_cam->GetPosition().x , m_cam->GetPosition().y + m_focus->GetPosition().y - (m_cam->m_localPosition.y - m_offset), m_cam->GetPosition().z));
	}
}

Camera* VerticalScroll::GetCam() const
{
	return m_cam;
}

Transform* VerticalScroll::GetFocus() const
{
	return m_focus;
}

float VerticalScroll::GetOffset() const
{
	return m_offset;
}
void VerticalScroll::SetCam(Camera* cam)
{
	m_cam = cam;
}

void VerticalScroll::SetFocus(Transform* focus)
{
	m_focus = focus;
}

void VerticalScroll::SetOffset(float offset)
{
	m_offset = offset;
}