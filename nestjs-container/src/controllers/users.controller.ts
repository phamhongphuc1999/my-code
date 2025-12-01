import {
  Body,
  Controller,
  Delete,
  Get,
  Param,
  ParseIntPipe,
  Patch,
  Post,
  Req,
  UseGuards,
} from '@nestjs/common';
import { LoginDto } from 'src/dto/login.dto';
// import { ValidationPipe } from 'src/pipe/validation.pipe';
import { AuthService } from 'src/services/auth.service';
import { CreateUserDto } from '../dto/create-user.dto';
import { UpdateUserDto } from '../dto/update-user.dto';
import { UsersService } from '../services/users.service';
import { JwtAuthGuard } from 'src/jwt-auth.guard';

@Controller('users')
export class UsersController {
  constructor(
    private readonly usersService: UsersService,
    private readonly authService: AuthService,
  ) {}

  @Get()
  getAll() {
    return this.usersService.findAll();
  }

  @Get(':id')
  getOne(@Param('id', ParseIntPipe) id: number) {
    return this.usersService.findOne(id);
  }

  @Post('login')
  async login(@Body() dto: LoginDto) {
    const { username, password } = dto;
    return await this.authService.login(username, password);
  }

  @Post()
  create(dto: CreateUserDto) {
    return this.usersService.create(dto);
  }

  @UseGuards(JwtAuthGuard)
  @Get('profile')
  getProfile(@Req() req: any) {
    // eslint-disable-next-line @typescript-eslint/no-unsafe-assignment, @typescript-eslint/no-unsafe-member-access
    return { message: 'Protected route', user: req.user };
  }

  @Patch(':id')
  update(@Param('id', ParseIntPipe) id: number, dto: UpdateUserDto) {
    return this.usersService.update(id, dto);
  }

  @Delete(':id')
  delete(@Param('id', ParseIntPipe) id: number) {
    return this.usersService.remove(id);
  }
}
