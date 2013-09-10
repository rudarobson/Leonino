/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package leoninoide;

import java.io.*;

/**
 *
 * @author rudarobson
 */
public class Workspace {

    public final static String ProjsFolder;
    public final static String ChipsPath;
    public final static String HIncludePath;
    public final static String LibFilePath;
    public final static String MainPath;
    public String projectName;

    static {
        String pre = System.getProperty("user.dir") + "\\";
        ProjsFolder = pre + "workspace\\projs";
        ChipsPath = pre + "workspace\\chips";
        HIncludePath = ChipsPath + "\\h\\leonino";
        LibFilePath = ChipsPath + "\\lib\\leonino.lpp";
        MainPath = ChipsPath + "\\lib\\main.c";
    }

    public String getProjectName() {
        return projectName;
    }

    public void setProjectName(String projectName) {
        this.projectName = projectName;
    }

    public String projectNameFullPath() {
        return ProjsFolder + "\\" + projectName + ".c";
    }

    public static String projectNameFullPath(String projName) {
        return ProjsFolder + "\\" + projName + ".c";
    }

    public static void save(String projName, String code) throws IOException {
        BufferedWriter codeFile = new BufferedWriter(new FileWriter(Workspace.projectNameFullPath(projName)));
        codeFile.write(code, 0, code.length());
        codeFile.close();
    }

    public static String open(String projName) throws FileNotFoundException, IOException {
        BufferedReader codeFile = new BufferedReader(new FileReader(Workspace.projectNameFullPath(projName)));
        String roleFile = "";
        String line = null;
        while ((line = codeFile.readLine()) != null) {
            roleFile += line + System.lineSeparator();
        }
        codeFile.close();
        return roleFile;

    }
}
