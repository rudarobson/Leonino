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
    private static String pathSeparator;
    private Workspace project;

    static {
        pathSeparator = Workspace.pathSeparator;
    }

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

    public String getProjectDistPath() {
        return project.getProjectDistFolder();
    }

    public String getProjectFolderPath() {
        return project.getProjectFolder();
    }

    public String getProjectSourcePath() {
        return project.getProjectSourcePath();
    }

    public String getLibPath() {
        return project.getLibRootPath() + mapIntToStringBoard(board) + pathSeparator + "leonino.lpp";
    }

    public String getMainPath() {
        return project.getMainRootPath() + "main.c";
    }

    public String getHeaderFolder() {
        return project.getHIncludeRootPath() + mapIntToStringBoard(board) + pathSeparator + "leonino";
    }

    private String mapIntToStringBoard(int board) {
        switch (board) {
            case LeoninoCompilerParams.LionBoard:
                return "lion";
        }
        throw new RuntimeException("Unkown board!");
    }
}
