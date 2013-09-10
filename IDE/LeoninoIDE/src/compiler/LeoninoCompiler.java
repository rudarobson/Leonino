/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package compiler;

import java.io.IOException;
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
            + "-I" + Workspace.HIncludePath + " --OUTDIR={1} --OBJDIR=.\\trash -Oleonino "
            + "--CODEOFFSET=" + bootloaderOffset + " "
            + "{2} {3} {4}";

    public static void compile(LeoninoCompilerParams params) {
        String cmd = compCommand.replace("{0}", params.mapBoardToChip()).replace("{1}", params.getProjectFolderPath()).replace("{2}", params.getLibPath()).replace("{3}", params.getProjectPath()).replace("{4}", params.getMainPath());
        try {
            Runtime.getRuntime().exec(cmd);
        } catch (IOException ex) {
        }
    }
}
