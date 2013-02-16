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

template <typename MODEL, typename APPEARANCE>
void run_estimation( const string & video ){
    ESMEstimator<MODEL, APPEARANCE> motion;
    motion.max_iterations = max_iterations;
    motion.min_delta = min_delta;
    motion.max_RMSE = max_RMSE;
    
    VideoBuffer<byte> * source = open_video_source<byte>( video );
    VideoFrame<byte> * frame;
    
    Image<byte> from, to;
    
    frame = source->get_frame();
    from.copy_from(*frame);
    source->put_frame(frame);
    
    while(source->frame_pending()){
        frame = source->get_frame();
        to.copy_from(*frame);
        source->put_frame(frame);
        
        motion.reset();
        motion.optimize(from, to);
        cout << motion.transform.get_matrix()[0] << motion.transform.get_matrix()[1] << motion.transform.get_matrix()[2] << " ";
        cout << motion.appearance << " " << motion.result << endl;
        
        from = to;
    }
}

int main(int argc, char ** argv ){
    
    options::make(model_params, "m");
    options::make(appearance_type, "a");
    options::make(max_iterations,"i");
    options::make(min_delta, "d");
    options::make(max_RMSE, "r");

    const int filearg = options::parse(argc, argv);

    if(argc < 2 || filearg == argc){
        cout << "usage: " << argv[0] << " [options] inputfiles\n";
        options::print();
        cout << endl;
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
