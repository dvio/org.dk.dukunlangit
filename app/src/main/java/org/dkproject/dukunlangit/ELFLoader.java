package org.dkproject.dukunlangit;

public class ELFLoader {
    static {
        System.loadLibrary("elf_loader");
    }

    public static native int loadSharedLibrary(String soFilePath);
}
