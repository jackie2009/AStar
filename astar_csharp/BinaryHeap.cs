 

using System.Collections.Generic;

public   class BinaryHeap {
	private List<AsGrid> gridlist = new List<AsGrid>();
	public int length = 0;

	private void tryDownAt(int index) {
		if (index < 0)
			return;
		int childIndex = index * 2 + 1;
		if (childIndex >= length) {
			return;
		}

		if (childIndex + 1 < length
				&& gridlist[(childIndex + 1)].score < gridlist
						[(childIndex)].score) {
			if (gridlist[(index)].score > gridlist[(childIndex + 1)].score) {
				swapAt(index, childIndex + 1);
				tryDownAt(childIndex + 1);

			}
		} else {

			if (gridlist[(index)].score > gridlist[(childIndex)].score) {
				swapAt(index, childIndex);
				tryDownAt(childIndex);

			}
		}
	}

	private void tryUpAt(int index) {
		if (index <= 0)
			return;
		int headIndex = (index - 1) / 2;
		if (gridlist[(index)].score < gridlist[(headIndex)].score) {
			swapAt(index, headIndex);
			tryUpAt(headIndex);
		}

	}

	public void push(AsGrid val) {
		gridlist.Add(val);
		length = gridlist.Count;
		tryUpAt(length - 1);
	}

	public void clear() {
		gridlist.Clear();
		length = 0;
	}

	public AsGrid popMix() {
		AsGrid val = gridlist[0];
		swapAt(0, length - 1);
		gridlist.RemoveAt(gridlist.Count - 1);
		length = gridlist.Count;
		tryDownAt(0);
		return val;

	}

	public void updata(AsGrid grid, int newScore) {
		int index = -1;
		for (int i = 0; i < length; i++) {
			if (gridlist[(i)] == grid) {
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
	}

	private void swapAt(int pos1, int pos2) {
		AsGrid c = gridlist[(pos1)];
		gridlist[pos1]= gridlist[(pos2)];
		gridlist[pos2]= c;

	}
}