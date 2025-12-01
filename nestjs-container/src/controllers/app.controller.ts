import { Body, Controller, Get, Post } from '@nestjs/common';
import { EmailProducer } from 'src/email-queue/email.producer';
import { AppService } from '../services/app.service';

@Controller()
export class AppController {
  constructor(
    private readonly appService: AppService,
    private emailProducer: EmailProducer,
  ) {}

  @Get()
  getHello(): string {
    return this.appService.getHello();
  }

  @Post('email')
  async test(@Body() data: { to: string; name: string }) {
    await this.emailProducer.sendWelcomeEmail(data);
    return { status: 'Job added', to: data.to, name: data.name };
  }
}
