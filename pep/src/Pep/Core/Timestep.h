#pragma once

namespace Pep {
	class Timestep
	{
	public:
		Timestep( float time = 0 ): m_Time( time ) {

		}
		~Timestep() {}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}
