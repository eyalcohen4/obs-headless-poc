#include "main.h"
#include <iostream>
#include <sstream>

using namespace std;

obs_video_info create_ovi() {
    struct obs_video_info ovi;

    ovi.adapter = 0;
    ovi.graphics_module = DL_OPENGL;
    ovi.output_format = VIDEO_FORMAT_I420;
    ovi.fps_num = 30000;
    ovi.fps_den = 1000;
    ovi.base_width = 640;
    ovi.base_height = 360;
    ovi.output_width = 640;
    ovi.output_height = 360;

    return ovi;
}

obs_audio_info create_oai() {
    struct obs_audio_info oai;

    oai.samples_per_sec = 44100;
    oai.speakers = SPEAKERS_STEREO;

    return oai;
}

void initialize_obs() {
    try {
        struct obs_audio_info oai = create_oai();
        struct obs_video_info ovi = create_ovi();

        obs_startup("en-US", nullptr, nullptr);
        obs_initialized();

        obs_reset_video(&ovi);
        obs_reset_audio(&oai);

        if (obs_initialized()) {
            cout << "OBS Initialized Successfully \n";
        }
    } catch (const std::exception& err) {
        cout << "[initialize_obs] error";
        cerr << err.what();
    }
}

int load_module(const char* binPath, const char* dataPath) {
    obs_module_t* module;

    int code = obs_open_module(&module, binPath, dataPath);
    if (code != MODULE_SUCCESS) {
        cout << "Failed to load module file" << binPath;
        return -1;
    }

    if (obs_init_module(module) != true) {
        return -1;
    }

    return 0;
}

void load_modules() {
    if (load_module(ROOT_DIR "/obs-studio/build/plugins/obs-ffmpeg/obs-ffmpeg",
                    ROOT_DIR "/obs-studio/plugins/obs-ffmpeg/data") != 0) {
        throw string("failed to load lib obs-ffmpeg.so");
    }

    if (load_module(ROOT_DIR
                    "/obs-studio/build/plugins/obs-outputs/obs-outputs",
                    ROOT_DIR "/obs-studio/plugins/obs-outputs/data") != 0) {
        throw string("failed to load lib obs-outputs.so");
    }
}

int main() {
    cout << "This is an executable running right now! \n";

    try {
        obs_data_t* rtmp_settings;
        obs_service_t* service;
        obs_output_t* output;
        std::stringstream rtmp_settings_data;
        rtmp_settings_data
            << "{ \"server\":\""
            << "rtmp://live.myplay.com/rtmp-in/MyplayTestLiveSession"
            << "\"}";

        initialize_obs();
        load_modules();

        obs_scene_t* scene = obs_scene_create("main");

        if (!scene) {
            throw string("Couldn't create main scene");
        }

        output = obs_output_create("ffmpeg_output", "ffmpeg output", nullptr,
                                   nullptr);
        obs_data_t* settings = obs_data_create();
        obs_data_set_string(settings, "format_name", "avi");
        obs_data_set_string(settings, "video_encoder", "utvideo");
        obs_data_set_string(settings, "audio_encoder", "pcm_s16le");

        obs_output_update(output, settings);

        obs_set_output_source(0, obs_scene_get_source(scene));
        // service = obs_service_create("flv_service", "flv output", NULL,
        // nullptr);

        // obs_output_set_service(output, service);
        if (obs_output_start(output) != true) {
            cout << "obs_output_start failed \n";

            const char* error = obs_output_get_last_error(output);

            if (error) {
                cout << error;
            }
        }
    } catch (const std::exception& e) {
        cerr << e.what();
    }
}
