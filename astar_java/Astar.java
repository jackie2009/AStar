package gluffy.utils;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;



public class Astar {
	public static Astar instance = new Astar();
	int mycount = 0;
	BinaryHeap openList = new BinaryHeap();
	Map<Integer, AsGrid> gridMap = new HashMap<Integer, AsGrid>();
	byte[][] mapdt;
	int COL;
	int ROW;
	int EndX;
	int EndY;
	int limitR;

	void open(int x, int y, int cost, AsGrid parent, boolean create) {
		AsGrid grid;

		if (create) {
			grid = new AsGrid();
			grid.x = x;
			grid.y = y;
			grid.cost = cost;
			grid.parent = parent;
			grid.closed = false;
			grid.score = 10000;
			gridMap.put((y << 16) + x, grid);
			int dx = Math.abs(x - EndX);
			int dy = Math.abs(y - EndY);
			if (dx > 0 && dy > 0) {
				grid.last = 14;
			} else {
				grid.last = 10;
			}

			grid.score = grid.cost + grid.last;
			openList.push(grid);
		} else {
			grid = gridMap.get((y << 16) + x);
			grid.parent = parent;
			;
			grid.cost = cost;
			openList.updata(grid, grid.cost + grid.last);
		}

		mycount++;

	}

	void check(int new_x, int new_y, AsGrid grid, int cost) {

		if (Math.abs(new_x - EndX) > limitR || Math.abs(new_y - EndY) > limitR)
			return;
		if (isBlock(new_x, new_y)) {
			return;
		}

		AsGrid newGrid = gridMap.get((new_y << 16) + new_x);
		if (newGrid == null) {
			open(new_x, new_y, grid.cost + cost, grid, true);
		} else if (!newGrid.closed && newGrid.cost > grid.cost + cost) {
			open(new_x, new_y, grid.cost + cost, grid, false);
		}

	}

	boolean isBlock(int x, int y) {
		return (y >= ROW || x >= COL) || (mapdt[y][x] & 0x1) != 0;
	}

	ArrayList<AstarPosVo> getRst(AsGrid grid) {
		ArrayList<AstarPosVo> return_dt = new ArrayList<AstarPosVo>();
		do {
			AstarPosVo pos = new AstarPosVo();
			pos.x =  grid.x;
			pos.y =  grid.y;
			grid = grid.parent;
			return_dt.add(0, pos);
		} while (grid != null);
		return (return_dt.size() > 2 ? return_dt : null);
	}

	public ArrayList<AstarPosVo> find(byte[][] mapdata, int row, int col,
			int start_x, int start_y, int end_x, int end_y, int limitR) {

		mapdt = mapdata;
		this.limitR = limitR;

		if (start_x == end_x && start_y == end_y)
			return null;
		ROW = row;
		COL = col;
		EndX = end_x;
		EndY = end_y;
		if (isBlock(start_x, start_y)) {
			return null;
		}
		if (isBlock(end_x, end_y)) {
			return null;
		}
		ArrayList<AstarPosVo> rst = null;

		open(start_x, start_y, 0, null, true);

		while (true) {
			int len = openList.length;
			if (len == 0) {
				break;
			}
			AsGrid c_grid = openList.popMix();

			if (c_grid.x == end_x && c_grid.y == end_y) {

				rst = getRst(c_grid);
				break;
			}
			c_grid.closed = true;
			int x = c_grid.x;
			int y = c_grid.y;

			check(x, y - 1, c_grid, 10);
			check(x - 1, y, c_grid, 10);
			check(x + 1, y, c_grid, 10);
			check(x, y + 1, c_grid, 10);
			check(x - 1, y - 1, c_grid, 14);
			check(x + 1, y - 1, c_grid, 14);
			check(x - 1, y + 1, c_grid, 14);
			check(x + 1, y + 1, c_grid, 14);
		}

		gridMap.clear();
		openList.clear();
		return rst;
	}

}
