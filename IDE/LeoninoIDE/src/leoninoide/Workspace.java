/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package leoninoide;

import java.io.*;
import org.fife.ui.rsyntaxtextarea.RSyntaxTextArea;

/**
 *
 * @author rudarobson
 */
public class Workspace {

    private final static String ProjsFolder;
    private final static String ChipsPath;
    private String projectName;
    private String projectPath;
    public final static String pathSeparator;
    public final static String UserInstallDir;

    static {
        pathSeparator = "\\";
        UserInstallDir = System.getProperty("user.dir") + pathSeparator;
        ProjsFolder = new File(UserInstallDir + "workspace" + pathSeparator + "projs").getAbsolutePath() + pathSeparator;
        ChipsPath = new File(UserInstallDir + "workspace" + pathSeparator + "chips").getAbsolutePath() + pathSeparator;
    }

    private Workspace(String name, String path) {
        this.projectName = name;

        if (path == null) {
            path = ProjsFolder;
        }
        this.projectPath = path;
    }

    public String getProjectName() {
        return projectName;
    }

    public void setProjectName(String projectName) {
        this.projectName = projectName;
    }

    public String getProjectFolder() {
        return ProjsFolder + projectName + pathSeparator;
    }

    public String getProjectLeoFilePath() {
        return ProjsFolder + projectName + pathSeparator + projectName + ".leo";
    }

    public String getProjectSourcePath() {
        return ProjsFolder + projectName + pathSeparator + "leonino.c";
    }

    public String getHIncludePath() {
        return ChipsPath + "h" + pathSeparator + "leonino";
    }

    public String getLibPath() {
        return ChipsPath + "lib" + pathSeparator + "leonino.lpp";
    }

    public String getMainPath() {
        return ChipsPath + "lib" + pathSeparator + "main.c";
    }

    public String getHexFilePath() {
        return ProjsFolder + projectName + pathSeparator + "leonino.hex";
    }

    public void save(String code) throws IOException {
        BufferedWriter codeFile = new BufferedWriter(new FileWriter(this.getProjectSourcePath()));
        codeFile.write(code, 0, code.length());
        codeFile.close();
    }

    public static Workspace open(String path, RSyntaxTextArea codeScreen) throws FileNotFoundException, IOException {
        File dir = new File(path);
        Workspace work = new Workspace(dir.getName(), dir.getAbsolutePath());

        if (!dir.isAbsolute()) {
            dir = new File(ProjsFolder + path.replace("/", Workspace.pathSeparator));
        }

        if (!dir.exists()) {
            dir.mkdirs();
        }

        File sourceFile = new File(work.getProjectSourcePath());
        if (!sourceFile.exists()) {
            sourceFile.createNewFile();
        }

        File leoFile = new File(work.getProjectLeoFilePath());
        if (!leoFile.exists()) {
            leoFile.createNewFile();
        }

        BufferedReader codeFile = new BufferedReader(new FileReader(work.getProjectSourcePath()));

        String line = null;
        StringBuffer fileData = new StringBuffer();

        char[] buf = new char[1024];
        int numRead = 0;
        while ((numRead = codeFile.read(buf)) != -1) {
            String readData = String.valueOf(buf, 0, numRead);
            fileData.append(readData);
        }
        codeFile.close();
        codeScreen.setText(fileData.toString());
        return work;
    }
}
