#include "lane.ih"

Lane::Lane(vector<Tile> &matrix, size_t idx, size_t rows, size_t cols, size_t power, size_t underground_distance)
:
	d_rows(rows),
	d_cols(cols),
	d_power(power)
{
	// cerr << "Lane constructor\n";
	size_t x = idx - (d_rows - 1) * d_cols;
	size_t y = d_rows - 1;
	size_t item = 1;

	while (true)
	{
		//cerr << "X: " << x << "   Y: " << y << "    Item: " << item << endl;
		d_path.push_back(Triple{x, y, item});
		size_t len = 0;
		switch (item)
		{
			case BN:
			case UBON:
			case SPLN:
			case SPRN: --y; break;
			case BE:
			case UBOE:
			case SPLE:
			case SPRE: ++x; break;
			case BS:
			case UBOS:
			case SPLS:
			case SPRS: ++y; break;
			case BW:
			case UBOW:
			case SPLW:
			case SPRW: --x; break;
			case UBIN:
				for (len = 2; len < underground_distance; ++len)
					if (y - len >= 0 && matrix[(y - len) * d_cols + x].item == UBON)
					{
						y -= len;
						break;
					}
				break;
			case UBIE:
				for (len = 2; len < underground_distance; ++len)
					if (x + len < d_cols && matrix[y * d_cols + x + len].item == UBOE)
					{
						x += len;
						break;
					}
				break;
			case UBIS:
				for (len = 2; len < underground_distance; ++len)
					if (y + len < d_rows && matrix[(y + len) * d_cols + x].item == UBOS)
					{
						y += len;
						break;
					}
				break;
			case UBIW:
				for (len = 2; len < underground_distance; ++len)
					if (x - len >= 0 && matrix[y * d_cols + x - len].item == UBOW)
					{
						x -= len;
						break;
					}
				break;
		}
		if (len == underground_distance)
			break;

		if (/*x < 0 || y < 0 || */x >= d_cols || y >= d_rows) // coordinates use unsigned ints. Negative values become max_int like.
			break;
		
		size_t newItem = matrix[y * d_cols + x].item;
		bool fail = true;
		switch (item)
		{
			case BN:
			case UBON:
			case SPLN:
			case SPRN:
				if (newItem == BN || newItem == BE || newItem == BW || newItem == UBIN || newItem == SPLN || newItem == SPRN)
					fail = false;
				break;
			case BE:
			case UBOE:
			case SPLE:
			case SPRE:
				if (newItem == BN || newItem == BE || newItem == BS || newItem == UBIE || newItem == SPLE || newItem == SPRE)
					fail = false;
				break;
			case BS:
			case UBOS:
			case SPLS:
			case SPRS:
				if (newItem == BE || newItem == BS || newItem == BW || newItem == UBIS || newItem == SPLS || newItem == SPRS)
					fail = false;
				break;
			case BW:
			case UBOW:
			case SPLW:
			case SPRW:
				if (newItem == BN || newItem == BS || newItem == BW || newItem == UBIW || newItem == SPLW || newItem == SPRW)
					fail = false;
				break;
			case UBIN:
				if (newItem == UBON)
					fail = false;
				break;
			case UBIE:
				if (newItem == UBOE)
					fail = false;
				break;
			case UBIS:
				if (newItem == UBOS)
					fail = false;
				break;
			case UBIW:
				if (newItem == UBOW)
					fail = false;
				break;
		}
		if (fail)
			break;

		item = newItem;
		for (auto it = d_path.begin(); it != d_path.end(); ++it)
			if (it->x == x && it->y == y)
				fail = true;
		
		if (fail)
			break;
	}
}