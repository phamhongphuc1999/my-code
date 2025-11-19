import { Injectable, UnauthorizedException } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { UsersService } from './users.service';

@Injectable()
export class AuthService {
  constructor(
    private usersService: UsersService,
    private jwtService: JwtService,
  ) {}

  async login(username: string, password: string) {
    const user = await this.usersService.findByUsername(username);
    if (!user) throw new UnauthorizedException('User not found');

    // eslint-disable-next-line @typescript-eslint/no-unsafe-assignment
    const isMatch = await this.usersService.validatePassword(
      password,
      user.password,
    );

    if (!isMatch) throw new UnauthorizedException('Invalid credentials');
    const payload = { sub: user.id, username: user.username };
    return { accessToken: this.jwtService.sign(payload) };
  }
}
