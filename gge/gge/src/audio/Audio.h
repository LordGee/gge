#pragma once

#include <string>
#include "gorilla/ga.h"
#include "../utilities/GetExtension.h"
#include "gorilla/gau.h"

namespace gge
{
	namespace audio
	{
		class Audio {
		private:
			std::string				m_AudioName;
			std::string				m_AudioFile;
			ga_Sound*				m_Sound;
			ga_Handle*				m_Handle;
			gau_SampleSourceLoop*	m_SourceLoop;

			gc_float32				m_Volume;
			gc_float32				m_Pan;
			gc_float32				m_Pitch;
			gc_int32				m_PausedPosition;
			bool					m_IsPlaying;
			bool					m_IsLooping;

		public:
			Audio(const std::string& name, const std::string& file);
			~Audio();

			void Play(unsigned int override = 0);
			void Pause();
			void Resume();
			void Stop();

			void SetVolume(float volume);
			void SetPan(float pan);
			void SetPitch(float pitch);
			void SetAudioLoop(bool loop);
			void SetIsPlaying(bool playing);

			void IncreaseVolume();
			void DecreaseVolume();
			void IncreasePitch();
			void DecreasePitch();
			void IncrementRightPan();
			void IncrementLeftPan();
			void CenterPan();

			bool CheckVolumeCondition(float value);
			bool CheckPitchCondition(float value);
			bool CheckPanCondition(float value);

			inline const float GetVolume() const { return m_Volume; }
			inline const float GetPitch() const { return m_Pitch; }
			inline const bool GetIsLooping() const { return m_IsLooping; }
			inline const bool IsAudioPlaying() const { return m_IsPlaying; }

			inline const std::string& GetAudioName() const { return m_AudioName; }
			inline const std::string& GetAudioFileName() const { return m_AudioFile; }
		};


	}
}
