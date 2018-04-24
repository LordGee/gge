#include "Audio.h"
#include "AudioManager.h"

namespace gge
{
	namespace audio
	{
		void destroyOnFinish(ga_Handle* in_handle, void* in_context);
		void loopOnFinish(ga_Handle* in_handle, void* in_context);

		Audio::Audio(const std::string& name, const std::string& file)
			: m_AudioName(name), m_AudioFile(file)
		{
			std::vector<std::string> extension = GetExtensionFromFilename(file, '.');
			if (extension.size() < 2) { return; }
			m_Sound = gau_load_sound_file(file.c_str(), extension.back().c_str());
			if (m_Sound == nullptr) {
				printf("Failed to load sound file!");
				return;
			}
			m_IsPlaying = false;
			m_IsLooping = false;

		}

		Audio::~Audio() {
			ga_handle_destroy(m_Handle);
			ga_sound_release(m_Sound);
		}

		void Audio::Play(unsigned int override) {
			if (m_IsPlaying && override == 0) { return; }
			gc_int32 quit = 0;
			if (!m_IsLooping) {
				m_Handle = gau_create_handle_sound(AudioManager::m_AudioMixer, m_Sound, &destroyOnFinish, &quit, NULL);
			}
			else {
				m_Handle = gau_create_handle_sound(AudioManager::m_AudioMixer, m_Sound, 0, 0, &m_SourceLoop);
			}
			m_Handle->audio = this;
			ga_handle_play(m_Handle);
			m_IsPlaying = true;
			ga_handle_getParamf(m_Handle, GA_HANDLE_PARAM_GAIN, &m_Volume);
			ga_handle_getParamf(m_Handle, GA_HANDLE_PARAM_PITCH, &m_Pitch);
			ga_handle_getParamf(m_Handle, GA_HANDLE_PARAM_PAN, &m_Pan);
		}

		void Audio::Pause() {
			if (!m_IsPlaying) { return; }
			m_PausedPosition = ga_handle_tell(m_Handle, GA_TELL_PARAM_CURRENT);
			Stop();
		}

		void Audio::Resume() {
			if (m_IsPlaying) { return; }
			Play();
			ga_handle_seek(m_Handle, m_PausedPosition);
		}

		void Audio::Stop() {
			if (!m_IsPlaying) { return; }
			m_IsPlaying = false;
			ga_handle_stop(m_Handle);
		}

		void Audio::SetVolume(float volume) {
			if (!m_IsPlaying) { return; }
			if (CheckVolumeCondition(volume)) {
				m_Volume = volume;
			}
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, volume);
		}

		void Audio::SetPan(float pan) {
			if (!m_IsPlaying) { return; }
			if (CheckPanCondition(pan)) {
				m_Pan = pan;
			}
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, pan);
		}

		void Audio::SetPitch(float pitch) {
			if (!m_IsPlaying) { return; }
			if (CheckPitchCondition(pitch)) {
				m_Pitch = pitch;
			}
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_PITCH, pitch);
		}

		void Audio::SetAudioLoop(bool loop) {
			m_IsLooping = loop;
		}

		void Audio::SetIsPlaying(bool playing) {
			m_IsPlaying = playing;
		}

		void Audio::IncreaseVolume() {
			if (!m_IsPlaying) { return; }
			if (CheckVolumeCondition(m_Volume + 0.05f)) {
				m_Volume += 0.05f;
				SetVolume(m_Volume);
			}
		}

		void Audio::DecreaseVolume() {
			if (!m_IsPlaying) { return; }
			if (CheckVolumeCondition(m_Volume - 0.05f)) {
				m_Volume -= 0.05f;
				SetVolume(m_Volume);
			}
		}

		void Audio::IncreasePitch() {
			if (!m_IsPlaying) { return; }
			if (CheckPitchCondition(m_Pitch + 0.05f)) {
				m_Pitch += 0.05f;
				SetPitch(m_Pitch);
			}
		}

		void Audio::DecreasePitch() {
			if (!m_IsPlaying) { return; }
			if (CheckPitchCondition(m_Pitch - 0.05f)) {
				m_Pitch -= 0.05f;
				SetPitch(m_Pitch);
			}
		}

		void Audio::IncrementRightPan() {
			if (!m_IsPlaying) { return; }
			if (CheckPanCondition(m_Pan + 0.05f)) {
				m_Pan += 0.05f;
				SetPan(m_Pan);
			}
		}

		void Audio::IncrementLeftPan() {
			if (!m_IsPlaying) { return; }
			if (CheckPanCondition(m_Pan - 0.05f)) {
				m_Pan -= 0.05f;
				SetPan(m_Pan);
			}
		}

		void Audio::CenterPan() {
			if (!m_IsPlaying) { return; }
			m_Pan = 0.00f;
			SetPan(m_Pan);
		}

		bool Audio::CheckVolumeCondition(float value) {
			return value >= 0.0f && value <= 1.0f;
		}

		bool Audio::CheckPitchCondition(float value) {
			return value >= 0.0f && value <= 16.0f;
		}

		bool Audio::CheckPanCondition(float value) {
			return value >= -1.0f && value <= 1.0f;
		}

		void destroyOnFinish(ga_Handle* in_handle, void* in_context) {
			Audio* audio = (Audio*)in_handle->audio;
			audio->Stop();
		}
	}
}
