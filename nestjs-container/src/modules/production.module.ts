import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { ProductionController } from 'src/controllers/production.controller';
import { Production } from 'src/entities/production.entity';
import { ProductionService } from 'src/services/production.service';

@Module({
  imports: [TypeOrmModule.forFeature([Production])],
  controllers: [ProductionController],
  providers: [ProductionService],
})
export class ProductionModule {}
