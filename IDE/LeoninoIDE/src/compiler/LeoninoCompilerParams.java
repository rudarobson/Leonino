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
    private Workspace project;

    public LeoninoCompilerParams(Workspace work) {
        this.project = work;
    }

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
        return project.getProjectFolder();
    }

    public String getProjectSourcePath() {
        return project.getProjectSourcePath();
    }

    public String getLibPath() {
        return project.getLibPath();
    }

    public String getMainPath() {
        return project.getMainPath();
    }

    public String getHeaderFolder() {
        return project.getHIncludePath();
    }
}
