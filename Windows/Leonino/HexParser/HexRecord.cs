using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hex
{
	public class HexRecord
	{
		public const int DataType = 0;
		public const int EOF = 1;
		public const int ExtendedSegmentAddress = 2;
		public const int ExtendedLinearAddressRecord = 4;


		public int Type { get; set; }
		public int ExtendedAddress { get; set; }
		public int Address { get; set; }
		public int Length { get; set; }
		public byte[] Data { get; set; }
		public int CheckSum { get; set; }
		public bool IsOk
		{
			get
			{
				//check content and checksum
				return true;
			}
		}

		public int FullAddress
		{
			get
			{
				return ExtendedAddress + Address;
			}
		}
	}
}
