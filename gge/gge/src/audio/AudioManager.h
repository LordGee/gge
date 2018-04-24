#pragma once
#include <vector>
#include "Audio.h"

#define GAU_THREAD_POLICY_MULTI	2

#include "gorilla/ga.h"
#include "gorilla/gau.h"



namespace gge
{
	namespace audio
	{
		class AudioManager {
		private:
			friend class Audio;

			static std::vector<Audio*>			m_AudioClips;
			static gau_Manager*					m_AudioManager;
			static ga_Mixer*					m_AudioMixer;

		public:
			static void AudioInit();

			static void UpdateAudio();

			static void AddAudioClip(Audio* audio);
			static Audio* GetAudioClip(const std::string& name);
			static void TerminateAudioClips();

		private:
			AudioManager() { }

		};
	}
}
