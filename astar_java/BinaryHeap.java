package gluffy.utils;

import java.util.ArrayList;

public final class BinaryHeap {
	private ArrayList<AsGrid> gridlist = new ArrayList<AsGrid>();
	public int length = 0;

	private void tryDownAt(int index) {
		if (index < 0)
			return;
		int childIndex = index * 2 + 1;
		if (childIndex >= length) {
			return;
		}

		if (childIndex + 1 < length
				&& gridlist.get(childIndex + 1).score < gridlist
						.get(childIndex).score) {
			if (gridlist.get(index).score > gridlist.get(childIndex + 1).score) {
				swapAt(index, childIndex + 1);
				tryDownAt(childIndex + 1);

			}
		} else {

			if (gridlist.get(index).score > gridlist.get(childIndex).score) {
				swapAt(index, childIndex);
				tryDownAt(childIndex);

			}
		}
	};

	private void tryUpAt(int index) {
		if (index <= 0)
			return;
		int headIndex = (index - 1) / 2;
		if (gridlist.get(index).score < gridlist.get(headIndex).score) {
			swapAt(index, headIndex);
			tryUpAt(headIndex);
		}

	};

	public void push(AsGrid val) {
		gridlist.add(val);
		length = gridlist.size();
		tryUpAt(length - 1);
	};

	public void clear() {
		gridlist.clear();
		length = 0;
	};

	public AsGrid popMix() {
		AsGrid val = gridlist.get(0);
		swapAt(0, length - 1);
		gridlist.remove(gridlist.size() - 1);
		length = gridlist.size();
		tryDownAt(0);
		return val;

	};

	public void updata(AsGrid grid, int newScore) {
		int index = -1;
		for (int i = 0; i < length; i++) {
			if (gridlist.get(i) == grid) {
				index = i;
				break;
			}
		}

		if (grid.score > newScore) {
			grid.score = newScore;
			tryDownAt(index);
		} else if (grid.score < newScore) {
			grid.score = newScore;
			tryUpAt(index);
		}
	};

	private void swapAt(int pos1, int pos2) {
		AsGrid c = gridlist.get(pos1);
		gridlist.set(pos1, gridlist.get(pos2));
		gridlist.set(pos2, c);

	}
}