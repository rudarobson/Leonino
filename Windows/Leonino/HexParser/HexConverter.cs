using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hex
{
	public static class HexConverter
	{
		public static byte HexToByte(char hex)
		{
			if (hex >= 0x30 && hex <= 0x39)
				return (byte)(hex - 0x30);
			if (hex >= 0x41 && hex <= 0x46)
				return (byte)(hex - 0x41 + 0xA);
			if (hex >= 0x61 && hex <= 0x66)
				return (byte)(hex - 0x61 + 0xA);

			throw new Exception("Unknown Hex Char: " + hex);
		}

		public static UInt32 HexToMax4Bytes(string hex)
		{
			if (hex == null)
				return 0;

			int len = hex.Length;

			if (len < 0)
				return 0;

			int i = 0;
			uint word = 0;
			for (i = 0; i < len; i++)
			{
				word |= (((uint)HexToByte(hex[i])) << 4 * (len - i - 1));
			}

			return word;
		}

		public static UInt64 HexToMax8Bytes(string hex)
		{
			if (hex == null)
				return 0;

			int len = hex.Length;

			if (len < 0)
				return 0;

			int i = 0;
			ulong word = 0;

			for (i = 0; i < len; i++)
				word |= (((ulong)HexToByte(hex[i])) << 4 * (len - i - 1));

			return word;
		}
	}
}
