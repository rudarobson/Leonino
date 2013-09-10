/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package compiler;

import leoninoide.Workspace;

/**
 *
 * @author rudarobson
 */
public class LeoninoCompilerParams {

    final public static int LionBoard = 1;
    private int board;
    private String projectName;

    public String mapBoardToChip() {
        if (board == LionBoard) {
            return "18f4550";
        }
        throw new RuntimeException("Board not Identified");
    }

    public int getBoard() {
        return board;
    }

    public void setBoard(int board) {
        this.board = board;
    }

    public String getProjectFolderPath() {
        return Workspace.ProjsFolder;
    }

    public String getLibPath() {
        return Workspace.LibFilePath;
    }

    public void setProjectName(String name) {
        projectName = name;
    }

    public String getProjectPath() {
        return Workspace.projectNameFullPath(projectName);
    }

    public String getMainPath(){
        return Workspace.MainPath;
    }
    
    public String getHeaderFolder() {
        return Workspace.HIncludePath;
    }
}
