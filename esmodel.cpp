#include <iostream>

#include <cvd/esm.h>
#include <cvd/image_io.h>
#include <cvd/videosource.h>
#include <cvd/glwindow.h>

#include "tools.h"

using namespace std;
using namespace CVD;

int model_params = 3;
int appearance_type = 0;
int max_iterations = 40;
double min_delta = 1e-5;
double max_RMSE = 1e-2;
int use_prefix = 0;

template <typename MODEL, typename APPEARANCE>
void run_estimation( const string & video ){
    ESMEstimator<MODEL, APPEARANCE> motion;
    motion.max_iterations = max_iterations;
    motion.min_delta = min_delta;
    motion.max_RMSE = max_RMSE;

    TooN::Matrix<3> prefix = TooN::Identity;

    VideoBuffer<byte> * source = open_video_source<byte>( video );
    VideoFrame<byte> * frame;
    
    Image<byte> from, to;
    
    frame = source->get_frame();
    from.copy_from(*frame);
    source->put_frame(frame);

    if(use_prefix){
        prefix(0,0) = 2.0 / from.size().x;
        prefix(1,1) = 2.0 / from.size().x;
        prefix(0,2) = -1;
        prefix(1,2) = double(from.size().y) / double(from.size().x);
    }
    
    cout << "H1 H2 H3 H4 H5 H6 H7 H8 H9 " << "err^2 pixels RMSE delta iterations [appearance]\n";

    while(source->frame_pending()){
        frame = source->get_frame();
        to.copy_from(*frame);
        source->put_frame(frame);
        
        motion.reset();
        motion.transform.set_prefix(prefix);
        motion.optimize(from, to);
        cout << motion.transform.get_matrix()[0] << motion.transform.get_matrix()[1] << motion.transform.get_matrix()[2];
        cout << motion.result;
        if(appearance_type == 1)
            cout << motion.appearance;
        cout << endl;

        from = to;
    }
}

int main(int argc, char ** argv ){
    
    options::make(model_params, "m");
    options::make(appearance_type, "a");
    options::make(max_iterations,"i");
    options::make(min_delta, "d");
    options::make(max_RMSE, "r");
    options::make(use_prefix, "p");

    const int filearg = options::parse(argc, argv);

    if(argc < 2 || filearg == argc){
        cout << "usage: " << argv[0] << " [options] input\n";
        options::print();
        cout << "examples:\n"
             << argv[0] << " files:[on_end=unset_pending]//*png\t\t all png files in the current directory\n";
        cout << argv[0] << " file://video.mp4                  \t\t a video file\n";
        return 1;
    }
    
    switch(model_params){
    case 3:
        switch(appearance_type){
        case 0: 
            run_estimation<HomographyPrefix<3>, StaticAppearance>( argv[filearg] );
            break;
        case 1:
            run_estimation<HomographyPrefix<3>, OffsetAppearance>( argv[filearg] );
            break;
        case 2:
            run_estimation<HomographyPrefix<3>, BlurAppearance>( argv[filearg] );
            break;
        }
        break;
    case 4:
        switch(appearance_type){
        case 0: 
            run_estimation<HomographyPrefix<4>, StaticAppearance>( argv[filearg] );
            break;
        case 1:
            run_estimation<HomographyPrefix<4>, OffsetAppearance>( argv[filearg] );
            break;
        case 2:
            run_estimation<HomographyPrefix<4>, BlurAppearance>( argv[filearg] );
            break;
        }
        break;
    case 6:
        switch(appearance_type){
        case 0: 
            run_estimation<HomographyPrefix<6>, StaticAppearance>( argv[filearg] );
            break;
        case 1:
            run_estimation<HomographyPrefix<6>, OffsetAppearance>( argv[filearg] );
            break;
        case 2:
            run_estimation<HomographyPrefix<6>, BlurAppearance>( argv[filearg] );
            break;
        }
        break;
    case 8:
        switch(appearance_type){
        case 0: 
            run_estimation<HomographyPrefix<8>, StaticAppearance>( argv[filearg] );
            break;
        case 1:
            run_estimation<HomographyPrefix<8>, OffsetAppearance>( argv[filearg] );
            break;
        case 2:
            run_estimation<HomographyPrefix<8>, BlurAppearance>( argv[filearg] );
            break;
        }
        break;
    }
    
    return 0;
}
