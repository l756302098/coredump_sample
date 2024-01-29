#include <iostream>
#include <sys/resource.h>
#include <limits.h>
#include <glog/logging.h>

static const char* EXE_NAME = "core_samples";
static void FailureHandle(const char* data, int size) {
    LOG(ERROR) << std::string(data, size);
}

void crash()
{
    int* a = nullptr;
    *a = 1;
}

int main(int argc, char* argv[])
{
    //set core
    struct rlimit rlim;
    getrlimit(RLIMIT_CORE,&rlim);
    printf("cur:%lu, max:%lu \n",rlim.rlim_cur,rlim.rlim_max);
    
    rlim.rlim_cur = 100 * 1024 * 1024;
    rlim.rlim_max = 100 * 1024 * 1024;
    setrlimit(RLIMIT_CORE,&rlim);

    getrlimit(RLIMIT_CORE,&rlim);
    printf("cur:%lu, max:%lu \n",rlim.rlim_cur,rlim.rlim_max);


    std::string cmd = "sysctl -w kernel.core_pattern=/home/li/log/%e.core.%p.%t";
    int rt = system(cmd.c_str());
    printf("result:%i",rt);
    //glog
    google::InitGoogleLogging(EXE_NAME);
    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(FailureHandle);
    FLAGS_log_dir = "/home/li/log";
    try
    {
        crash();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr <<'other error. \n';
    }
    while (1)
    {
        sleep(1);
        LOG(INFO) << "sleep 1.";
    }
    
    
    return 0;
}