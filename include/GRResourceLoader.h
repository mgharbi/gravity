#ifndef GRRESOURCELOADER_H_7HLOFN8M
#define GRRESOURCELOADER_H_7HLOFN8M

#include <boost/filesystem.hpp>
#include <string>

#include "CoreFoundation/CoreFoundation.h"

namespace fs = boost::filesystem;


fs::path get_resource_path(std::string filename, std::string extension = "", fs::path prefix = "") {
    CFStringRef fname  = CFStringCreateWithCString(kCFAllocatorDefault, filename.c_str(), kCFStringEncodingUTF8);
    CFStringRef ext    = CFStringCreateWithCString(kCFAllocatorDefault, extension.c_str(), kCFStringEncodingUTF8);
    CFStringRef subdir = CFStringCreateWithCString(kCFAllocatorDefault, prefix.c_str(), kCFStringEncodingUTF8);

    CFURLRef urlRef = CFBundleCopyResourceURL(
        CFBundleGetMainBundle(),
        fname,
        ext,
        subdir
    );
    CFRelease(fname);
    CFRelease(ext);
    CFRelease(subdir);
    
    if(!urlRef)
        return fs::path("");


    CFStringRef filePathRef = CFURLCopyPath(urlRef);
    const int buffer_sz = 512;
    char buffer[buffer_sz];
    CFStringGetCString(filePathRef, buffer, buffer_sz, kCFStringEncodingUTF8);

    CFRelease(urlRef);
    CFRelease(filePathRef);

    return fs::path(buffer);
}



#endif /* end of include guard: GRRESOURCELOADER_H_7HLOFN8M */

