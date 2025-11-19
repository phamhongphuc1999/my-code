import { Injectable, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Production } from 'src/entities/production.entity';
import { Repository } from 'typeorm';

@Injectable()
export class ProductionService {
  constructor(
    @InjectRepository(Production)
    private readonly repo: Repository<Production>,
  ) {}

  findAll() {
    return this.repo.find();
  }

  async findOne(id: number) {
    const user = await this.repo.findOneBy({ id });
    if (!user) throw new NotFoundException('User not found');
    return user;
  }
}
