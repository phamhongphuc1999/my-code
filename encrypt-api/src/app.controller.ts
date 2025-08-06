import { Controller, Get } from '@nestjs/common';
import { AppService } from './app.service';

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get('/hello')
  getHello(): string {
    return this.appService.getHello();
  }

  @Get('/json')
  getJson() {
    return this.appService.getJson();
  }

  @Get('/web-api-crypt')
  async getWebApiCrypt() {
    const data = await this.appService.getCryptWebApi();
    return { data, status: 'ok' };
  }

  @Get('/crypt')
  getCrypt() {
    const data = this.appService.getCryptLibraryApi();
    return { data, status: 'ok' };
  }
}
