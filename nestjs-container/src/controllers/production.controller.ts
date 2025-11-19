import { Controller, Get, Param, ParseIntPipe } from '@nestjs/common';
import { ProductionService } from 'src/services/production.service';

@Controller('productions')
export class ProductionController {
  constructor(private readonly productionService: ProductionService) {}

  @Get()
  getAll() {
    return this.productionService.findAll();
  }

  @Get(':id')
  getOne(@Param('id', ParseIntPipe) id: number) {
    return this.productionService.findOne(id);
  }
}
