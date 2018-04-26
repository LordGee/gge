#include "AudioManager.h"

namespace gge
{
	namespace audio
	{
		std::vector<Audio*>			AudioManager::m_AudioClips;
		gau_Manager*				AudioManager::m_AudioManager = nullptr;
		ga_Mixer*					AudioManager::m_AudioMixer = nullptr;

		void AudioManager::AudioInit() {
			gc_initialize(0);
			m_AudioManager = gau_manager_create();
			m_AudioMixer = gau_manager_mixer(m_AudioManager);
			AddAudioClip(new Audio("Default", "audio/snapper4298/credits2.wav"));
		}

		void AudioManager::UpdateAudio() {
			gau_manager_update(m_AudioManager);
		}

		void AudioManager::AddAudioClip(Audio* audio) {
			m_AudioClips.push_back(audio);
		}

		Audio* AudioManager::GetAudioClip(const std::string& name) {
			for (int i = 0; i < m_AudioClips.size(); i++) {
				if (m_AudioClips[i]->GetAudioName() == name) {
					return m_AudioClips[i];
				}
			}
			return m_AudioClips[0];
		}

		void AudioManager::TerminateAudioClips() {
			for (int i = 0; i < m_AudioClips.size(); i++) {
				delete m_AudioClips[i];
			}
			gau_manager_destroy(m_AudioManager);
			gc_shutdown();
		}
	}
}
