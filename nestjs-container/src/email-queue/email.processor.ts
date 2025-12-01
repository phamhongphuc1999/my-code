import { OnWorkerEvent, Processor, WorkerHost } from '@nestjs/bullmq';
import { Logger } from '@nestjs/common';
import { Job } from 'bullmq';

@Processor('email', { concurrency: 5 })
export class EmailProcessor extends WorkerHost {
  private readonly logger = new Logger(EmailProcessor.name);

  async process(job: Job): Promise<any> {
    this.logger.log(`Processing job: ${job.name}`);
    if (job.name == 'welcome-email') {
      const { to, name } = job.data as { to: string; name: string };
      this.logger.log(`Sending welcome email to: ${to}, name: ${name}`);
      await new Promise((resolve) => setTimeout(resolve, 500));

      this.logger.log(`Email sent to ${to}`);
    }
  }

  @OnWorkerEvent('completed')
  onCompleted(job: Job) {
    this.logger.log(`Job ${job.id} completed`);
  }

  @OnWorkerEvent('failed')
  onFailed(job: Job, err: Error) {
    this.logger.error(`Job ${job.id} failed: ${err.message}`);
  }
}
