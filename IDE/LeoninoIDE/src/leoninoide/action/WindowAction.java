/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package leoninoide.action;

import java.io.*;
import java.nio.CharBuffer;

/**
 *
 * @author rudarobson
 */
public class WindowAction {

    public static String ProjFolder = "./workspace/projs/";

    public static void save(String projName, String code) throws IOException {
        BufferedWriter codeFile = new BufferedWriter(new FileWriter(ProjFolder + "/" + projName + ".c"));
        codeFile.write(code, 0, code.length());
        codeFile.close();
    }

    public static String open(String projName) throws FileNotFoundException, IOException {
        BufferedReader codeFile = new BufferedReader(new FileReader(ProjFolder + "/" + projName + ".c"));
        String roleFile = "";
        String line = null;
        while ((line = codeFile.readLine()) != null) {
            roleFile += line + System.lineSeparator();
        }
        codeFile.close();
        return roleFile;

    }
}
