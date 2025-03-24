#include <jni.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h>
#include <elf.h>

extern "C" {

// Function to read DT_NEEDED dependencies from an ELF file
std::vector<std::string> getElfDependencies(const char* soFilePath) {
    std::vector<std::string> dependencies;
    int fd = open(soFilePath, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open ELF file");
        return dependencies;
    }

    Elf64_Ehdr ehdr;
    read(fd, &ehdr, sizeof(ehdr));

    // Locate section headers
    lseek(fd, ehdr.e_shoff, SEEK_SET);
    std::vector<Elf64_Shdr> shdrs(ehdr.e_shnum);
    read(fd, shdrs.data(), ehdr.e_shnum * sizeof(Elf64_Shdr));

    // Locate dynamic section
    Elf64_Shdr dynSection;
    for (const auto& shdr : shdrs) {
        if (shdr.sh_type == SHT_DYNAMIC) {
            dynSection = shdr;
            break;
        }
    }

    // Read dynamic section
    std::vector<Elf64_Dyn> dynEntries(dynSection.sh_size / sizeof(Elf64_Dyn));
    lseek(fd, dynSection.sh_offset, SEEK_SET);
    read(fd, dynEntries.data(), dynSection.sh_size);

    // Locate string table
    std::string strTab;
    for (const auto& dyn : dynEntries) {
        if (dyn.d_tag == DT_STRTAB) {
            lseek(fd, dyn.d_un.d_ptr, SEEK_SET);
            char buffer[4096]; // Assume string table fits
            read(fd, buffer, sizeof(buffer));
            strTab = std::string(buffer);
        }
    }

    // Extract DT_NEEDED entries
    for (const auto& dyn : dynEntries) {
        if (dyn.d_tag == DT_NEEDED) {
            dependencies.emplace_back(&strTab[dyn.d_un.d_val]);
        }
    }

    close(fd);
    return dependencies;
}

// Function to load ELF dependencies and the main .so
JNIEXPORT jint JNICALL
Java_org_dkproject_dukunlangit_ELFLoader_loadSharedLibrary(JNIEnv *env, jclass clazz, jstring soPath) {
    const char* path = env->GetStringUTFChars(soPath, nullptr);
    std::vector<std::string> dependencies = getElfDependencies(path);

    // Load dependencies first
    for (const auto& lib : dependencies) {
        std::cout << "Loading dependency: " << lib << std::endl;
        if (!dlopen(lib.c_str(), RTLD_LAZY)) {
            std::cerr << "Failed to load dependency: " << dlerror() << std::endl;
            env->ReleaseStringUTFChars(soPath, path);
            return -1;
        }
    }

    // Load the main .so file
    void* handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
        env->ReleaseStringUTFChars(soPath, path);
        return -1;
    }

    env->ReleaseStringUTFChars(soPath, path);
    return 0;
}

}
