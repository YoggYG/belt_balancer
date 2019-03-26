#include "balancer.ih"

void Balancer::print2()
{
	print2(d_matrix);
}

void Balancer::print2(vector<Tile> &matrix)
{
	for (size_t col = 0; col < d_cols; ++col)
		cerr << "==";
	for (size_t row = 0; row < d_rows; ++row)
	{
		cerr << endl;
		for (size_t col = 0; col < d_cols; ++col)
		{
			switch (matrix[row * d_cols + col].item)
			{
				case EMPTY: cerr << "  "; break;
				case BN: cerr << "^^"; break;
				case BE: cerr << ">>"; break;
				case BS: cerr << "vv"; break;
				case BW: cerr << "<<"; break;
				case UBIN: cerr << "--"; break;
				case UBIE: cerr << ">|"; break;
				case UBIS: cerr << "vv"; break;
				case UBIW: cerr << "|<"; break;
				case UBON: cerr << "^^"; break;
				case UBOE: cerr << "|>"; break;
				case UBOS: cerr << "--"; break;
				case UBOW: cerr << "<|"; break;
				case SPLN: cerr << "^)"; break;
				case SPRN: cerr << "(^"; break;
				case SPLE: cerr << ">>"; break;
				case SPRE: cerr << "~~"; break;
				case SPLS: cerr << "(v"; break;
				case SPRS: cerr << "v)"; break;
				case SPLW: cerr << "~~"; break;
				case SPRW: cerr << "<<"; break;
				default: cerr << "uuum value was above 20 (" << matrix[row * d_cols + col].item << ")\n";
			}
		}
		cerr << endl;
		for (size_t col = 0; col < d_cols; ++col)
		{
			switch (matrix[row * d_cols + col].item)
			{
				case EMPTY: cerr << "  "; break;
				case BN: cerr << "^^"; break;
				case BE: cerr << ">>"; break;
				case BS: cerr << "vv"; break;
				case BW: cerr << "<<"; break;
				case UBIN: cerr << "^^"; break;
				case UBIE: cerr << ">|"; break;
				case UBIS: cerr << "--"; break;
				case UBIW: cerr << "|<"; break;
				case UBON: cerr << "--"; break;
				case UBOE: cerr << "|>"; break;
				case UBOS: cerr << "vv"; break;
				case UBOW: cerr << "<|"; break;
				case SPLN: cerr << "^)"; break;
				case SPRN: cerr << "(^"; break;
				case SPLE: cerr << "__"; break;
				case SPRE: cerr << ">>"; break;
				case SPLS: cerr << "(v"; break;
				case SPRS: cerr << "v)"; break;
				case SPLW: cerr << "<<"; break;
				case SPRW: cerr << "__"; break;
				default: cerr << "uuum value was above 20 (" << matrix[row * d_cols + col].item << ")\n";
			}
		}
	}
	cerr << endl;
	for (size_t col = 0; col < d_cols; ++col)
		cerr << "=="; 
	cerr << endl;
}