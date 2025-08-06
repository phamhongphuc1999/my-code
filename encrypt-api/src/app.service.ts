import { Injectable } from '@nestjs/common';
import { encryptText, webApiEncode } from './app.utils';

const exampleJson = {
  name: 'example name',
  title: 'example title',
  description: 'example description',
  token: {
    decimal: 18,
    symbol: 'ETH',
    name: 'Ethereum',
    img: 'http://example.img.eth',
  },
  metadata: {
    '2025': {
      '1': 'example1',
      '2': 'example2',
    },
    '2024': {
      '1': {
        '1': 1,
        '2': 2,
      },
    },
  },
};

@Injectable()
export class AppService {
  getHello(): string {
    return 'Hello World!';
  }

  getJson() {
    return exampleJson;
  }

  async getCryptWebApi(): Promise<string> {
    return await webApiEncode(JSON.stringify(exampleJson), '12345678');
  }

  getCryptLibraryApi(): string {
    return encryptText(JSON.stringify(exampleJson), '12345678');
  }
}
