/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package compiler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

/**
 *
 * @author rudarobson
 */
public class LeoninoCompiler extends Thread {

    private final static String bootloaderOffset = "2000h";
    private final static String compCommand =
            "xc8 --chip={0} --runtime=default,+clear,+init,-keep,-no_startup,+download,-config,+clib,+plib "
            + "-I{5} --OUTDIR=\"{1}\" --OBJDIR=.\\trash -Oleonino "
            + "--CODEOFFSET=" + bootloaderOffset + " "
            + "\"{2}\" \"{3}\" \"{4}\"";
    private LeoninoCompilerParams params;
    private LeoninoCompilerListener listener;

    private LeoninoCompiler(LeoninoCompilerParams input, LeoninoCompilerListener listener) {
        this.params = input;
        this.listener = listener;
    }

    public void run() {
        CompilerOutput output = new CompilerOutput();
        output.setExitMessage("Error ocurred!");
        String cmd = compCommand.replace("{0}", params.mapBoardToChip()).replace("{1}", params.getProjectDistPath()).replace("{2}", params.getLibPath()).replace("{3}", params.getProjectSourcePath()).replace("{4}", params.getMainPath()).replace("{5}", params.getHeaderFolder());
        Process proc = null;
        try {
            proc = Runtime.getRuntime().exec(cmd);
        } catch (Exception ex) {
        } finally {
            if (proc != null) {
                InputStream stdin = proc.getInputStream();
                InputStreamReader isr = new InputStreamReader(stdin);
                BufferedReader br = new BufferedReader(isr);
                StringBuffer fileData = new StringBuffer();

                char[] buf = new char[1024];
                int numRead = 0;
                try {
                    while ((numRead = br.read(buf)) != -1) {
                        String readData = String.valueOf(buf, 0, numRead);
                        fileData.append(readData);
                    }
                    output.setExitMessage(fileData.toString());
                    output.setExitValue(proc.exitValue());
                } catch (IOException ex) {
                }
            }
            String msg = output.getExitMessage();
            if (output.succeded()) {
                msg += System.lineSeparator() + "Success!";

            } else {
                msg += System.lineSeparator() + "Error!";

            }
            output.setExitMessage(msg);
            listener.exit(output);
        }

    }

    public static void compile(LeoninoCompilerParams params, LeoninoCompilerListener listener) {
        LeoninoCompiler comp = new LeoninoCompiler(params, listener);
        comp.start();
    }
}
