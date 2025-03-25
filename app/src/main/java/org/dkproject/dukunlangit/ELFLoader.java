package org.dkproject.dukunlangit;

import net.fornwall.jelf.ElfDynamicSection;
import net.fornwall.jelf.ElfFile;
import java.io.File;
import java.util.List;

public class ELFLoader {

    public static boolean loadLibrary(String nativeLibraryDir, String libName) {
        String libPath = nativeLibraryDir + "/" + libName; // Assume libName is already correctly formatted
        try {
            ElfFile file = ElfFile.from(new File(libPath));
            ElfDynamicSection dynSection = file.firstSectionByType(ElfDynamicSection.class);
            List<String> dependencies = dynSection.getNeededLibraries();

            for (String dependency : dependencies) {
                String depPath = nativeLibraryDir + "/" + dependency;
                if (!new File(depPath).exists()) {
                    depPath = "/system/lib64/" + dependency;  // Check system lib64
                    if (!new File(depPath).exists()) {
                        System.err.println("Dependency not found: " + dependency);
                        return false; // Fail if any dependency is missing
                    }
                }
                System.load(depPath);
                System.out.println("Loaded dependency: " + depPath);
            }

            System.load(libPath); // Load Bootloader only after dependencies are resolved
            System.out.println("Loaded library: " + libPath);
            return true;

        } catch (Exception e) {
            System.err.println("Failed to load library: " + e.getMessage());
            return false;
        }
    }
}
