import { BullModule } from '@nestjs/bullmq';
import { Module } from '@nestjs/common';
import { EmailProcessor } from 'src/email-queue/email.processor';
import { EmailProducer } from 'src/email-queue/email.producer';

@Module({
  imports: [BullModule.registerQueue({ name: 'email' })],
  providers: [EmailProducer, EmailProcessor],
  exports: [EmailProducer],
})
export class QueueModule {}
