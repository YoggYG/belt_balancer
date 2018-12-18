#include "balancer.ih"

void Balancer::print2()
{
	for (size_t col = 0; col < d_cols; ++col)
		cout << "==";
	for (size_t row = 0; row < d_rows; ++row)
	{
		cout << endl;
		for (size_t col = 0; col < d_cols; ++col)
		{
			switch (d_matrix[row * d_cols + col].item)
			{
				case EMPTY: cout << "  "; break;
				case BN: cout << "^^"; break;
				case BE: cout << ">>"; break;
				case BS: cout << "vv"; break;
				case BW: cout << "<<"; break;
				case UBIN: cout << "--"; break;
				case UBIE: cout << ">|"; break;
				case UBIS: cout << "vv"; break;
				case UBIW: cout << "|<"; break;
				case UBON: cout << "^^"; break;
				case UBOE: cout << "|>"; break;
				case UBOS: cout << "--"; break;
				case UBOW: cout << "<|"; break;
				case SPLN: cout << "^)"; break;
				case SPRN: cout << "(^"; break;
				case SPLE: cout << ">>"; break;
				case SPRE: cout << "~~"; break;
				case SPLS: cout << "(v"; break;
				case SPRS: cout << "v)"; break;
				case SPLW: cout << "~~"; break;
				case SPRW: cout << "<<"; break;
				default: cerr << "uuum value was above 20 (" << d_matrix[row * d_cols + col].item << ")\n";
			}
		}
		cout << endl;
		for (size_t col = 0; col < d_cols; ++col)
		{
			switch (d_matrix[row * d_cols + col].item)
			{
				case EMPTY: cout << "  "; break;
				case BN: cout << "^^"; break;
				case BE: cout << ">>"; break;
				case BS: cout << "vv"; break;
				case BW: cout << "<<"; break;
				case UBIN: cout << "^^"; break;
				case UBIE: cout << ">|"; break;
				case UBIS: cout << "--"; break;
				case UBIW: cout << "|<"; break;
				case UBON: cout << "--"; break;
				case UBOE: cout << "|>"; break;
				case UBOS: cout << "vv"; break;
				case UBOW: cout << "<|"; break;
				case SPLN: cout << "^)"; break;
				case SPRN: cout << "(^"; break;
				case SPLE: cout << "__"; break;
				case SPRE: cout << ">>"; break;
				case SPLS: cout << "(v"; break;
				case SPRS: cout << "v)"; break;
				case SPLW: cout << "<<"; break;
				case SPRW: cout << "__"; break;
				default: cerr << "uuum value was above 20 (" << d_matrix[row * d_cols + col].item << ")\n";
			}
		}
	}
	cout << endl;
	for (size_t col = 0; col < d_cols; ++col)
		cout << "=="; 
	cout << endl;
}