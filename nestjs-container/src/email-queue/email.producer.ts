import { InjectQueue } from '@nestjs/bullmq';
import { Injectable } from '@nestjs/common';
import { Queue } from 'bullmq';

@Injectable()
export class EmailProducer {
  constructor(@InjectQueue('email') private readonly emailQueue: Queue) {}

  async sendWelcomeEmail(data: { to: string; name: string }) {
    return await this.emailQueue.add('welcome-email', data, {
      attempts: 3,
      delay: 1000,
    });
  }
}
