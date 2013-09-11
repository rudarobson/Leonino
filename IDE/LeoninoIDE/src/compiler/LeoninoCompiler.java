/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package compiler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.logging.Level;
import java.util.logging.Logger;
import leoninoide.Workspace;

/**
 *
 * @author rudarobson
 */
public class LeoninoCompiler {

    private final static String bootloaderOffset = "2000h";
    private final static String compCommand =
            "xc8 --chip={0} --runtime=default,+clear,+init,-keep,-no_startup,+download,-config,+clib,+plib "
            + "-I{5} --OUTDIR=\"{1}\" --OBJDIR=.\\trash -Oleonino --OUTPUT=inhx32 "
            + "--CODEOFFSET=" + bootloaderOffset + " "
            + "\"{2}\" \"{3}\" \"{4}\"";

    public static String compile(LeoninoCompilerParams params) {
        String cmd = compCommand.replace("{0}", params.mapBoardToChip()).replace("{1}", params.getProjectFolderPath()).replace("{2}", params.getLibPath()).replace("{3}", params.getProjectSourcePath()).replace("{4}", params.getMainPath()).replace("{5}", params.getHeaderFolder());
        String output = "";
        try {
            Process proc = Runtime.getRuntime().exec(cmd);

            InputStream stdin = proc.getInputStream();
            InputStreamReader isr = new InputStreamReader(stdin);
            BufferedReader br = new BufferedReader(isr);
            String line = null;

            StringBuffer fileData = new StringBuffer();

            char[] buf = new char[1024];
            int numRead = 0;
            while ((numRead = br.read(buf)) != -1) {
                String readData = String.valueOf(buf, 0, numRead);
                fileData.append(readData);
            }


            int exitVal;
            exitVal = proc.waitFor();

            output = fileData.toString();
        } catch (Exception ex) {
        } finally {
        }

        return output;
    }
}
