#include "balancer.ih"

void Balancer::print()
{
	// for (size_t col = 0; col < d_cols; ++col)
	// 	cout << "=";
	for (size_t idx = 0; idx < d_rows * d_cols; ++idx)
	{
		if (idx % d_cols == 0)
			cout << endl;
		switch (d_matrix[idx].item)
		{
			case EMPTY: cout << ' '; break;
			case BN: cout << '^'; break;
			case BE: cout << '>'; break;
			case BS: cout << 'v'; break;
			case BW: cout << '<'; break;
			case UBIN: cout << '-'; break;
			case UBIE: cout << '|'; break;
			case UBIS: cout << '-'; break;
			case UBIW: cout << '|'; break;
			case UBON: cout << '-'; break;
			case UBOE: cout << '|'; break;
			case UBOS: cout << '-'; break;
			case UBOW: cout << '|'; break;
			case SPLN: cout << ')'; break;
			case SPRN: cout << '('; break;
			case SPLE: cout << '_'; break;
			case SPRE: cout << '~'; break;
			case SPLS: cout << '('; break;
			case SPRS: cout << ')'; break;
			case SPLW: cout << '~'; break;
			case SPRW: cout << '_'; break;
			default: cerr << "uuum value was above 20 (" << d_matrix[idx].item << ")\n";
		}
	}
	cout << endl;
	// for (size_t col = 0; col < d_cols; ++col)
	// 	cout << "="; 
	cout << endl;
}